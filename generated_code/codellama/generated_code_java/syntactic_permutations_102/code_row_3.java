import java.io.*;
class JavaFile {
    public static void main(String[] args) throws IOException {
        FileOutputStream file = new FileOutputStream("important_config", true);
        OutputStreamWriter writer = new OutputStreamWriter(file, "utf-8");
        writer.write("important_config");
        writer.close();
    }
}