# building (one-time setup)
### docker build -t c0 .
#
# running (first time)
### docker run --name=c0_container -v <PATH_TO_C0_FILES>:/my_c0_dir -w /my_c0_dir -it c0
### replace <PATH_TO_C0_FILES> with the path to the local C0 files you want to run
### (you can do pwd within that folder to find the path)
### Example:
### docker run --name=c0_container -v ~/private/15122:/my_c0_dir -w /my_c0_dir -it c0
# running (subsequent times)
### docker start -i c0_container
# quitting
### exit
#
# removing a container (to fix an issue with the Dockerfile)
### docker container ls -a | grep c0
### docker container rm [container_id]
# where [container_id] is the first field of the previous command

FROM ubuntu:20.04
ARG c0_binaries=https://c0.cs.cmu.edu/downloads/aux/cc0-latest.tgz
ARG c0_version=v20210822
CMD bash

ARG DEBIAN_FRONTEND=noninteractive

## Common packages
RUN apt-get -y update && \
    apt-get -y install \
      build-essential \
      wget


## Getting cc0
RUN wget ${c0_binaries}
RUN tar -xvzf cc0-latest.tgz
RUN mv cc0.${c0_version} /usr/local/share/cc0
RUN rm cc0-latest.tgz

## Getting other libraries used by cc0
RUN apt-get install -y libpng-dev
RUN apt-get install -y libncurses5

#RUN echo 'export PATH=$PATH:/usr/local/share/cc0/bin' >> ~/.bashrc
ENV PATH="/usr/local/share/cc0/bin:${PATH}"
