import java.io.IOException;
import java.util.Scanner;

public class Printf {
  public static void main(String[] args) throws IOException {
    String[] files = print("ls %s", "/home/user/files");
  }
}