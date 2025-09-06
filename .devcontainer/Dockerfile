FROM debian:trixie

ARG USER=user
ENV DEBIAN_FRONTEND=noninteractive

# debian trixie specific locale setup
# see https://stackoverflow.com/questions/28405902/how-to-set-the-locale-inside-a-ubuntu-docker-container
RUN apt update && apt install -y locales && \
    echo "en_GB.UTF-8 UTF-8" > /etc/locale.gen && \
    locale-gen && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    export LANG=en_GB.UTF-8 && export LC_ALL=en_GB.UTF-8
ENV LANG=en_GB.UTF-8
ENV LC_ALL=en_GB.UTF-8

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
    ninja-build \
    gettext

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



RUN useradd -m $USER && echo "$USER:$USER" | chpasswd && adduser $USER sudo
RUN echo "user            ALL = (ALL) NOPASSWD: ALL" >> /etc/sudoers

RUN printf "alias ll='ls -la'" >> /home/$USER/.bashrc

CMD /bin/bash