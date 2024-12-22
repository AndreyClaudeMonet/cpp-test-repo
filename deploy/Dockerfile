FROM ubuntu:22.04

# Обновляем пакетный менеджер и устанавливаем необходимые зависимости, включая g++
RUN apt-get update && \
    apt-get install -y \
    # Включает g++, make и другие инструменты для сборки
    build-essential \  
    curl \
    ca-certificates \
    lsb-release \
    gnupg2

# Устанавливаем CMake из стандартного репозитория Ubuntu 22.04
RUN apt-get update && \
    apt-get install -y cmake

RUN apt install clang-format -y

# Устанавливаем рабочую директорию
RUN mkdir /app
WORKDIR /app
