From ubuntu:latest

RUN apt-get update && apt-get install -y libx11-dev libpng-dev git

RUN mkdir /app && git clone https://github.com/WeiChihChern/RGBMask2Gray.git /app

WORKDIR /app/RGBMask2Gray/bin
