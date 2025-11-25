# --- Етап 1: Збірка (Builder) ---
# Використовуємо Ubuntu 22.04 для збірки
FROM ubuntu:22.04 as builder

# Оновлюємо пакети і встановлюємо компілятор та CMake вручну
# Це гарантує, що ми знаємо, чим компілюємо
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git

WORKDIR /app

# Копіюємо вихідний код
COPY CMakeLists.txt .
COPY src/ src/
COPY include/ include/

# Збираємо
RUN mkdir build && cd build && cmake .. && make

# --- Етап 2: Запуск (Runtime) ---
# Використовуємо ТУ Ж САМУ версію Ubuntu для запуску
FROM ubuntu:22.04

WORKDIR /app

# Копіюємо бінарник
COPY --from=builder /app/build/SimpleHttpServer .
COPY server.conf .

# Створюємо папку для логів
RUN mkdir -p logs

EXPOSE 8080

CMD ["./SimpleHttpServer"]