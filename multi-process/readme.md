# Pipe ile Parent-Child Süreç İletişimi (Multi-Process IPC)

Bu proje, C dilinde `pipe()` ve `fork()` kullanarak iki süreç (parent ve child) arasında **tek yönlü iletişim** sağlar.

## 📌 Amaç

- `fork()` ile bir child (çocuk) süreç oluşturmak
- `pipe()` kullanarak parent sürecin bir mesajı child sürece aktarması
- `read()` ve `write()` fonksiyonlarıyla bu iletişimi gerçekleştirmek

## 💡 Teknik Bilgiler

- Bu bir **multi-process** örneğidir. `fork()` kullanıldığı için ayrı süreçler oluşur.
- İletişim için **pipe** sistemi kullanılır (`pipefd[0]` okuma, `pipefd[1]` yazma).
- Mesaj `"Merhaba çocuk!"` parent tarafından yazılır ve child tarafından okunur.

## 🧪 Örnek Çıktı


