#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "Log.hpp"
#include "Timer.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"


int main(int argc, char **argv, char **env) {
    LOG_TO_STDOUT;
    LOG(DEBUG);
  pid_t pid;
  int   p[2];

  pipe(p);
  pid = fork();

  if (pid == 0) {
      dup2(p[1], 1); // redirect the output (STDOUT to the pipe)
      close(p[0]);
      execlp("cat", "cat", NULL);
      exit(EXIT_FAILURE);
  }
  else {
      close(p[1]);
      std::string str;
      while(1) {
      std::cin >> str;
      std::cerr << str;
      //fd_set rfds;
  }
//      char buffer[11] = {0};

//      while (1) {
//          FD_ZERO(&rfds);
//          FD_SET(p[0], &rfds);
//          select(p[0] + 1, &rfds, NULL, NULL, NULL); //wait for changes on p[0]

//          if(FD_ISSET(p[0], &rfds)) {
//              int       ret = 0;
//              while ((ret = read(p[0], buffer, 10)) > 0) //read on the pipe
//                {
//                  std::cerr << buffer;
//                  memset(buffer, 0, 10);
//                }
//            }
//        }
    }
    return 0;
}
