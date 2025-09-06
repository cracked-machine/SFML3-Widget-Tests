FROM debian:trixie

ARG USER=user
ENV DEBIAN_FRONTEND=noninteractive

# general stuff plus mingw cross compiler
RUN apt update -y && apt install -y \
    clangd \
    clang-format \
    sudo \
    locales \
    gcc-mingw-w64-x86-64 \
    g++-mingw-w64-x86-64 \
    doxygen \
    gettext \
    git \
    build-essential \
    make \
    pkg-config \
    cmake \
    ninja-build 

# SFML3 reqs
RUN apt update -y && apt install -y \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev

RUN locale-gen en_GB.UTF-8 && update-locale

RUN useradd -m $USER && echo "$USER:$USER" | chpasswd && adduser $USER sudo
RUN echo "user            ALL = (ALL) NOPASSWD: ALL" >> /etc/sudoers

RUN printf "alias ll='ls -la'" >> /home/$USER/.bashrc

CMD /bin/bash