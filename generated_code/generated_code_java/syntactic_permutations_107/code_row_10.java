import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

class Main {
  public static void main(String[] args) throws Exception {
    File file = new File("secret.txt");
    FileWriter fileWriter = new FileWriter(file);
    fileWriter.write("This is a secret.");
    fileWriter.close();
    Files.setPosixFilePermissions(Paths.get(file.getAbsolutePath()), PosixFilePermissions.fromString("r--------"));
    System.out.println(Files.getPosixFilePermissions(Paths.get(file.getAbsolutePath())));
  }
}