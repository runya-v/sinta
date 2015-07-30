#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "Log.hpp"
#include "Timer.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"
#include "StdoutToStdin.hpp"
#include "NumberGenerator.hpp"


int main(int argc, char **argv, char **env) {
    LOG_TO_STDOUT;
    LOG(DEBUG);

//  pid_t pid;
//  int   p[2];

//  pipe(p);
//  pid = fork();

//  if (pid == 0) {
//      dup2(p[1], 1); // redirect the output (STDOUT to the pipe)
//      close(p[0]);
//      execlp("cat", "cat", NULL);
//      exit(EXIT_FAILURE);
//  }
//  else {
//      close(p[1]);
//      std::string str;
//      while(not std::cin.fail() and ng) {
//          LOG(DEBUG);
//          while(getline(std::cin, str)) {
//              LOG(DEBUG);
//              std::clog << "# ";
//              std::clog << str << std::endl << std::flush;
//              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//              std::cin.clear();
//              std::cin.get();
//          }
//      }

//  }
//      std::cin >> str;
//      std::cerr << str;
//  }
    StdoutToStdin oti();

    if (oti) {
        NumberGenerator ng(10);
    }
    else {
      char buffer[11] = {0};
      fd_set rfds;
      while (1) {
          int p = fileno(stdin);
          FD_ZERO(&rfds);
          FD_SET(p, &rfds);
          select(p + 1, &rfds, NULL, NULL, NULL); //wait for changes on p[0]
          LOG(DEBUG);

          if(FD_ISSET(p, &rfds)) {
              int ret = 0;
              while ((ret = read(p, buffer, 10)) > 0) //read on the pipe
                {
                  std::clog << "# " << buffer;
                  memset(buffer, 0, 10);
                }
            }
        }
    }
    return 0;
}
