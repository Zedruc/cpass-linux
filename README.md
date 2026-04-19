# cpass

A command-line password generator written in C. Uses `getrandom(2)` for cryptographically secure randomness.

## Building

```sh
make        # production build (-O2)
make dev    # debug build (-g -O0)
```

Requires GCC and a Linux system (uses `getrandom` syscall).

### Installation

```sh
sudo make install            # installs to /usr/local/bin
make install PREFIX=~/.local # installs to ~/.local/bin
sudo make uninstall          # removes installed binary
```

## Usage

```
cpass [options]
```

Running with no arguments outputs a bare 16-character password to stdout (suitable for piping). Use `-v` / `--verbose` for decorated output with warnings and info messages.

### Options

| Flag | Description |
|------|-------------|
| `-l <length>` | Set password length (default: 16) |
| `-e <flags>` | Exclude character sets (see below) |
| `-s` | Save generated password to `pass.txt` |
| `-r` | Delete `pass.txt` |
| `-v` / `--verbose` | Verbose output (decorated password, warnings, info messages) |
| `-h` | Show help |

### Exclusion flags (`-e`)

Combine any of the following letters after `-e`:

| Flag | Effect |
|------|--------|
| `u` | Exclude uppercase A-Z |
| `l` | Exclude lowercase a-z |
| `n` | Exclude numbers 0-9 |
| `s` | Exclude special characters |

### Examples

```sh
# Default 16-character password
cpass

# 32-character password
cpass -l 32

# No special characters, no uppercase
cpass -e su

# 24-character password, numbers only
cpass -l 24 -e uls

# Save to pass.txt
cpass -s

# Pipe the password to clipboard (default bare output)
cpass | xclip -selection clipboard

# Verbose output with decorations and warnings
cpass -v -l 8

# Reset saved passwords
cpass -r
```

## Notes

- Passwords shorter than 12 characters trigger a safety warning.
- `pass.txt` is append-only — `-s` never overwrites existing entries.
- All character sets must not be simultaneously excluded.
