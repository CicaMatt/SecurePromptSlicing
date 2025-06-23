import java.io.FileOutputStream;

public class HelloWorld{
  public static void main(String[] args) {
    FileOutputStream file = new FileOutputStream("important_config",FileOutputStream.O_CREAT);
	file.write("important_config".getBytes());
	file.close();
  }
}