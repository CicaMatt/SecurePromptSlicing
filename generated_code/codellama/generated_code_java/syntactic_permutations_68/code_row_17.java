import java.io.*;
import java.util.*;
import org.apache.commons.codec.binary.*;

public class ImageUpload {
  public static void main(String[] args) throws IOException {
    Scanner input = new Scanner(System.in);
    System.out.print("Enter image name: ");
    String filename = input.nextLine();
    System.out.println("Uploading " + filename + "...");

    String base64 = null;
    try {
      FileInputStream fileInputStream = new FileInputStream(filename);
      byte[] bytes = new byte[fileInputStream.available()];
      fileInputStream.read(bytes);
      fileInputStream.close();
      Base64 encoder = new Base64();
      base64 = encoder.encodeAsString(bytes);
    } catch (IOException e) {
      System.out.println("Error: " + e.getMessage());
    }

    if (base64 != null) {
      System.out.println("Uploaded image " + filename + " as base64 string:");
      System.out.println(base64);
    } else {
      System.out.println("Error uploading image.");
    }
  }
}