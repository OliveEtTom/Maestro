FROM debian:latest

# Prerequisites
RUN apt update && apt install -y gcc g++ cmake gdb libboost-all-dev

# Set up new user
RUN useradd -ms /bin/bash developer
USER developer
WORKDIR /home/developer

CMD ["/bin/sh" "-c" "bash"]
