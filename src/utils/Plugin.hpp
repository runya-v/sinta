/*!
 * \brief  Базовый класс плагина
 * \author Rostislav Velichko. rostislav.vel@gmail.com
 * \date   12.10.2012
 */

////////////////////////////////////////////////////////////////////////////////////////////////////
// class MyPlugin
//   : public Plugin {
// public:
//   MyPlugin()
//   {}
// } my_plugin;
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>

#define OPEN_FUNC_NAME "Get"

namespace utils {

class Config;
class Plugin;
} // namespace

extern "C" {
  //! \brief Типы получения объекта загруженного плагина.
  typedef utils::Plugin*(*GetPluginFunc)(utils::Plugin *parent, const char *name, int argc, char **argv, char **env);

  /*!
   * \brief Метод получения объекта из загруженной библиотеки и его инициализации
   * \param parent Указатель на базовый плагин
   * \param name   Имя загруженной библиотеки (полный путь)
   * \param argc   Количество аргументов
   * \param argv   Массив аргументов
   * \param env    Массив переменных окружения
   */
  utils::Plugin* Get(utils::Plugin *parent, const char *name, int argc, char **argv, char **env);
} // extern "C"


namespace utils {

class Plugin {
  //! \brief Хендлер загруженного плагина.
  typedef void* Handler;

  //! \brief Типы контейнера загруженных плагинов.
  typedef std::pair<Handler, Plugin*> Lib;
  typedef std::map<std::string, Lib>  Plugins;
  typedef Plugins::iterator           PluginIter;
  typedef Plugins::value_type         PluginValue;

  Plugins _plugins;

protected:
  Plugin      *_parent; ///< Указатель на базовый плагин
  std::string _name;    ///< Имя загруженной библиотеки (полный путь)
  int         _argc;    ///< Количество аргументов
  char        **_argv;  ///< Массив аргументов
  char        **_env;   ///< Массив переменных окружения

public:
  friend class Config;

  static Plugin *s_plugin;

  virtual bool execute() = 0;

  Plugin();
  virtual ~Plugin();

  /*!
   * \brief Метод загрузки плагинов из указанной директории
   * \param lib_path Имя директории содержащей плагины
   */
  void load(const std::string &lib_path = ".");

  /*!
   * \brief Метод загрузки, инициализации и запуска плагина
   * \param name Имя загружзаемой библиотеки (полный путь)
   */
  Plugin* get(const std::string &name);

  /*!
   * \brief Метод выгрузки плагина
   * \param name Имя загруженной библиотеки (сохраняется в параметрах объекта плагина)
   */
  bool close(const std::string &name);

  //! \brief Метод выгрузки плагинов.
  void close();

  //! \brief Метод получения текущего количества загруженных плагинов.
  std::size_t size();
};
} // namespace
