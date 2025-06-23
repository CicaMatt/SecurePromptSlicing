import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.zip.CRC32;

class Main {
  public static void main(String[] args) throws IOException {
    File file = new File("test.txt");
    byte[] buffer = Files.readAllBytes(file.toPath());
    CRC32 crc = new CRC32();
    crc.update(buffer);
    long checksum = crc.getValue();
    if (checksum == 0) {
      System.out.println("Buffer is empty.");
    } else {
      Files.writeString(new File("output.txt").toPath(), String.format("%d %d", buffer.length, checksum));
    }
  }
}