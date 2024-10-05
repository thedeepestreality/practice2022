#!/bin/sh

g++ sender.cpp -o sender -Ijson/include

g++ server.cpp -o server -Ijson/include