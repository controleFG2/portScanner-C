# Port Scanner em C 🔍

Um scanner de portas TCP simples desenvolvido em linguagem C utilizando sockets nativos (POSIX/Berkeley sockets). O projeto foi criado com fins estritamente educacionais para praticar programação de baixo nível, manipulação de strings, parsing de argumentos (`getopt`) e resolução de DNS em C.

## 🚀 Funcionalidades

- **Varredura TCP Connect:** Verifica portas abertas tentando estabelecer uma conexão completa (`connect()`).
- **Resolução de DNS:** Aceita tanto endereços IPv4 quanto nomes de domínio (ex: `scanme.nmap.org`).
- **Múltiplos modos de scan:** Varredura padrão (1–1024), portas específicas separadas por vírgula, intervalo customizado ou todas as 65.535 portas.
- **Saída tabulada:** Exibe as portas abertas de forma organizada diretamente no terminal.

## 🛠️ Pré-requisitos

Para compilar e executar o projeto, você precisará de um compilador C (`gcc`) em um ambiente Linux ou Unix-like (WSL, macOS, etc.):

```bash
sudo apt update && sudo apt install build-essential
```

## 📦 Como Compilar

1. **Clone o repositório:**
   ```bash
   git clone [https://github.com/controleFG2/portScanner-C.git](https://github.com/controleFG2/portScanner-C.git)
   cd portScanner-C
   ```

2. **Compile o código-fonte:**
   ```bash
   gcc scanner.c -o scanner
   ```

## 💻 Como Usar

```bash
./scanner -u <alvo> [opções]
```

### Opções disponíveis

| Flag | Argumento | Descrição |
| :--- | :--- | :--- |
| `-u` | `<alvo>` | **(Obrigatório)** Endereço IP ou domínio do alvo. |
| `-p` | `<portas>` | Escaneia portas específicas separadas por vírgula (máx. 100 portas). |
| `-r` | `<ini-fim>` | Define um intervalo customizado de portas (ex: `20-80`). |
| `-a` | — | Escaneia todas as portas TCP (`1` a `65535`). |

*(Nota: Caso nenhuma opção de porta seja informada, o scanner verifica por padrão o intervalo de **1 a 1024**).*

### Exemplos

```bash
# Scan padrão (portas 1 a 1024) usando um domínio
./scanner -u scanme.nmap.org

# Escanear portas específicas
./scanner -u 192.168.1.1 -p 21,22,80,443,8080

# Escanear um intervalo específico
./scanner -u 192.168.1.1 -r 1-500

# Escanear todas as portas (1 a 65535)
./scanner -u 192.168.1.1 -a
```

## ⚠️ Aviso Legal

Esta ferramenta foi desenvolvida apenas para **fins de estudo e aprendizado**. Não utilize este software para escanear redes ou sistemas sem a devida autorização prévia do proprietário.