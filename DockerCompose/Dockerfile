FROM gcc:14-bookworm

WORKDIR /app
COPY main.cpp .
RUN g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o compose-example

CMD ["./compose-example"]