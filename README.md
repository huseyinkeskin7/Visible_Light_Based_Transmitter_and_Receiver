# Visible_Light_Based_Transmitter_and_Receiver
# Türkçe
Bu proje, iki Arduino kartı arasında görünür ışık kullanılarak kablosuz veri iletimi sağlayan bir haberleşme sistemidir. Veri aktarımı, bir lazer (verici) ve bir LDR (alıcı) üzerinden gerçekleştirilir. Sistemin temel bileşenleri:
    Verici (Transmitter): Serial monitörden alınan metin verilerini ASCII’ye dönüştürerek lazer aracılığıyla bit-bit gönderir.
    Alıcı (Receiver): Lazerden gelen ışık değişimlerini LDR ile algılar, 8-bit verileri çözümleyerek LCD ekranda görüntüler.
Senkronizasyon, veri kaybını önlemek adına sistem başlatılırken otomatik olarak yapılır. Her karakter için 8-bitlik bir veri iletimi gerçekleştirilir ve karakter sınırı olmadan mesajlar aktarılabilir.
Bu proje, düşük maliyetli, kablosuz ve modüler bir optik iletişim sisteminin temelini atmaktadır.

# English
This project implements a wireless data communication system between two Arduinos using visible light. A laser acts as the transmitter and an LDR (Light Dependent Resistor) serves as the receiver. Core components of the system:
    Transmitter: Reads text from the serial monitor, converts it to ASCII, and sends each character bit-by-bit via a laser.
    Receiver: Detects light variations via an LDR, reconstructs the 8-bit characters, and displays the received message on an I2C LCD.
The system performs automatic synchronization before the first transmission to determine the timing interval. Each character is transmitted as an 8-bit binary with no character limit.
This project demonstrates a cost-effective, modular, and wireless optical communication system prototype using visible light.
