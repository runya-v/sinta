#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>

#include "Log.hpp"
#include "StdoutToStdin.hpp"


int writepipe[2] = {-1,-1}; // parent -> child
int readpipe [2] = {-1,-1}; // child -> parent
pid_t childpid;

#define DUP2CLOSE(old_fd, new_fd) (dup2((old_fd), (new_fd)), close((old_fd)))
#define	PARENT_READ  readpipe[0]
#define	CHILD_WRITE  readpipe[1]
#define CHILD_READ   writepipe[0]
#define PARENT_WRITE writepipe[1]
#define MAXLINE 5000


StdoutToStdin::StdoutToStdin()
    : _is_parent(true)
{
    LOG(DEBUG);

    int fd1[2];
    int fd2[2];
    pid_t pid;
    char line[MAXLINE];

    if (0 > pipe(fd1) or 0 > pipe(fd2))
    {
        throw std::runtime_error("Can`t create pipe");
    }

    pid = fork();

    if (0 > pid) {
        throw std::runtime_error("Can`t fork child");
    }
    else  if (0 == pid)     // CHILD PROCESS
    {
        _is_parent = false;

        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] not_eq STDIN_FILENO)
        {
            if (dup2(fd1[0], STDIN_FILENO) not_eq STDIN_FILENO)
            {
                std::cerr << "dup2 error to stdin" << std::endl;
            }
            close(fd1[0]);
        }

        if (fd2[1] not_eq STDOUT_FILENO)
        {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                std::cerr << "dup2 error to stdout" << std::endl;
            }
            close(fd2[1]);
        }

        if ( execl("path/PROGRAM B", "PROGRAM B", (char *)0) < 0 )
        {
            std::cerr << "system error" << std::endl;
        }
    }
    else        // PARENT PROCESS
    {
        int rv;
        close(fd1[0]);
        close(fd2[1]);

        if ( write(fd1[1], "PROGRAM_B_INPUT", strlen("PROGRAM_B_INPUT") ) not_eq strlen("PROGRAM_B_INPUT") )
        {
            std::cerr << "READ ERROR FROM PIPE" << std::endl;
        }

        if ( (rv = read(fd2[0], line, MAXLINE)) < 0 )
        {
            std::cerr << "READ ERROR FROM PIPE" << std::endl;
        }
        else if (rv == 0)
        {
            std::cerr << "Child Closed Pipe" << std::endl;
        }

        std::cout << "OUTPUT of PROGRAM B is: " << line;
    }

//    if (0 > pipe(readpipe) or 0 > pipe(writepipe))
//    {
//        throw std::runtime_error("Can`t create pipe");
//    }

//    childpid = fork();

//    if (0 > childpid) {
//        throw std::runtime_error("Can`t fork child");
//    }
//    else if (not childpid) {
//        //close(CHILD_WRITE);
//        close(PARENT_READ);
//        DUP2CLOSE(CHILD_WRITE, fileno(stdin));
//        //DUP2CLOSE(CHILD_READ, fileno(stdout));

////        dup2(CHILD_READ,  0);  close(CHILD_READ);
////        dup2(CHILD_WRITE, 1);  close(CHILD_WRITE);
//    }
//    else {
//        _is_parent = false;
//        //close(PARENT_WRITE);
//        //close(CHILD_READ);
//    }

    //    pid_t pid;
//    pipe(_p);
//    pid = fork();

//    if (pid) {
//        dup2(_p[1], fileno(stdout)); // redirect the output (STDOUT to the pipe)
//        close(_p[0]);
//        execlp("cat", "cat", NULL);
//        throw std::runtime_error("EXIT_FAILURE");
//    }
//    else {
//        dup2(_p[0], fileno(stdin)); // redirect the output (STDIN to the pipe)
//        close(_p[1]);
//    }
}

StdoutToStdin::operator bool() {
    return _is_parent;
}
