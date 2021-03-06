#include <boost/format.hpp>

#include <CTPP2Parser.hpp>
#include <CTPP2ParserException.hpp>
#include <CTPP2HashTable.hpp>
#include <CTPP2VMDumper.hpp>
#include <CTPP2FileSourceLoader.hpp>
#include <CTPP2FileOutputCollector.hpp>
#include <CTPP2VMOpcodes.h>
#include <CTPP2VMFileLoader.hpp>
#include <CTPP2JSONFileParser.hpp>
#include <CTPP2VM.hpp>
#include <CTPP2VMSTDLib.hpp>
#include <CTPP2VMException.hpp>
#include <CTPP2VMStackException.hpp>

#include "Log.hpp"
#include "utility.hpp"
#include "Generator.hpp"
#include "TextFileLoader.hpp"


using namespace tmplt;


const int CTPP_MAX_HANDLERS = 100;


Generator::Generator(
    const base::bfs::path &file_ct2,
    const base::bfs::path &file_json,
    const base::bfs::path &file_html,
    bool remove)
    : _remove(remove)
    , _path_result(file_html)
    , _syscall_factory(CTPP_MAX_HANDLERS)
    , _fn_file_load(std::make_shared<TextFileLoader>())
{
    CFile cfile_out(file_html.string());
    CTPP::FileOutputCollector output_collector(cfile_out);
    CTPP::SyscallFactory syscall_factory(100);
    syscall_factory.RegisterHandler(_fn_file_load.get());
    CTPP::STDLibInitializer::InitLibrary(syscall_factory);
    CTPP::VMFileLoader loader(file_ct2.string().c_str());
    const CTPP::VMMemoryCore *vm_memory_core = loader.GetCore();
    CTPP::CDT hash;
    CTPP::CTPP2JSONFileParser json_file_parser(hash);

    try {
        json_file_parser.Parse(file_json.string().c_str());
        CTPP::VM vm(&syscall_factory);
        vm.Init(vm_memory_core, &output_collector, nullptr);
        std::uint32_t ip = 0;
        vm.Run(vm_memory_core, &output_collector, ip, hash, nullptr);
        LOG(INFO) << "Generate html `" << file_html.string() << "`.";
        CTPP::STDLibInitializer::DestroyLibrary(syscall_factory);
    }
    catch(CTPP::CDTTypeCastException &e) {
        LOG(ERROR) << "Type Cast " << e.what();
    }
    catch(CTPP::CDTAccessException &e) {
        LOG(ERROR) << "Array index out of bounds: `" << e.what() << "`";
    }
    catch(CTPP::IllegalOpcode &e) {
        LOG(ERROR) << "Illegal opcode " << e.GetOpcode() << " at " << e.GetIP();
    }
    catch(CTPP::InvalidSyscall &e) {
        if (e.GetIP() not_eq 0) {
            CTPP::VMDebugInfo debug_info(e.GetDebugInfo());
            LOG(ERROR)
                << e.what() << " at "
                << e.GetIP() << "(Template file `" << e.GetSourceName() << "`,"
                << "Line " << debug_info.GetLine() << ", "
                << "Pos " << debug_info.GetLinePos() << ")";
        }
        else {
            LOG(ERROR) << "Unsupported syscall: " << e.what();
        }
    }
    catch(CTPP::InvalidCall &e) {
        CTPP::VMDebugInfo debug_info(e.GetDebugInfo());
        LOG(ERROR)
            << "at " << e.GetIP() << ": "
            << "Invalid block name `" << e.what() << "` "
            << "in file `" << e.GetSourceName() << "`, "
            << "Line " << debug_info.GetLine()
            << "Pos " << debug_info.GetLinePos();
    }
    catch(CTPP::CodeSegmentOverrun &e) {
        LOG(ERROR) << e.what() << " at " << e.GetIP();
    }
    catch(CTPP::StackOverflow &e) {
        LOG(ERROR) << "Stack overflow at " << e.GetIP();
    }
    catch(CTPP::StackUnderflow &e) {
        LOG(ERROR) << "Stack underflow at " << e.GetIP();
    }
    catch(CTPP::ExecutionLimitReached &e) {
        LOG(ERROR) << "Execution limit reached at " << e.GetIP();
    }
    catch(CTPP::VMException &e) {
        LOG(ERROR) << "VM generic exception: " << e.what() << " at " << e.GetIP();
    }
    catch(CTPP::CTPPLogicError &e) {
        LOG(ERROR) << e.what();
    }
    catch(CTPP::CTPPUnixException &e) {
        LOG(ERROR) << "I/O in " << e.what() << ": " << strerror(e.ErrNo());
    }
    catch(CTPP::CTPPException &e) {
        LOG(ERROR) << "CTPP Generic exception: " << e.what();
    }
    catch(...) {
        LOG(ERROR) << "Undefined.";
    }
}


Generator::~Generator() {
	_syscall_factory.RemoveHandler(_fn_file_load->GetName());

    if (base::bfs::exists(_path_result) and _remove) {
        base::bfs::remove(_path_result);
        LOG(INFO) << "Delete: `" << _path_result.string() << "`.";
    }
}


Generator::operator const std::string&() {
    return _path_result.string();
}


