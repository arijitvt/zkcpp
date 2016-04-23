
cc=g++
del=rm -rf

target=output


cflags=-g -c -std=c++0x  -I.
lflags=-pthread -lzookeeper_mt

objs= \
	  Zookeeper.o \
	  main.o


all:$(objs) 
	$(cc) $(objs) -o $(target)  $(lflags)


%.o:%.cpp
	$(cc) $(cflags) -o $@ $<


clean:
	$(del) $(objs)
	$(del) $(target)
