import java.io.*;
class MyFile {
    public static void main(String[] args) throws Exception {
        FileOutputStream fout = new FileOutputStream("important_config", true);
        byte data[] = "important_config".getBytes();
        fout.write(data);
        fout.close();
    }
}