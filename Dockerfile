FROM ubuntu:bionic
RUN apt -y update && apt -y install git wget apt-utils cmake libboost-all-dev g++-8 gcc-8
RUN wget -qO - http://repo.radeon.com/rocm/apt/debian/rocm.gpg.key | apt-key add - && \
    echo 'deb [arch=amd64] http://repo.radeon.com/rocm/apt/debian/ xenial main' | tee /etc/apt/sources.list.d/rocm.list
RUN apt -y update && \
    DEBIAN_FRONTEND=noninteractive apt -y install libnuma-dev rocm-dev rocprofiler-dev gdb hip-thrust libopencv-dev python3-opencv
RUN useradd -ms /bin/bash rocm_user
USER rocm_user
WORKDIR /home/rocm_user
ENV PATH "$PATH:/opt/rocm/bin"
# RUN echo "export PATH=$PATH:/opt/rocm/bin/" >> ~/.bash_profile
