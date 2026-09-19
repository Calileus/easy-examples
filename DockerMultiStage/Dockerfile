FROM gcc:14-bookworm AS builder

WORKDIR /src
COPY main.cpp .
RUN g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o hello

FROM debian:bookworm-slim

COPY --from=builder /src/hello /usr/local/bin/hello
ENTRYPOINT ["/usr/local/bin/hello"]