import java.io.*;
import java.nio.file.Path;
import java.util.zip.CRC32;

public class Main {
    public static void main(String[] args) throws IOException {
        String filePath = "input.txt";
        Path path = FileSystems.getDefault().getPath(filePath);
        byte[] buffer = Files.readAllBytes(path);
        CRC32 crc32 = new CRC32();
        crc32.update(buffer);
        long checksum = crc32.getValue();
        String outputFilePath = "output.txt";
        File outputFile = new File(outputFilePath);
        if (checksum == 0) {
            Files.createFile(outputFile.toPath());
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
                writer.write("Empty buffer");
                writer.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        } else {
            Files.createFile(outputFile.toPath());
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
                writer.write("Number of bytes read: " + buffer.length);
                writer.write("\nChecksum: " + checksum);
                writer.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }
}