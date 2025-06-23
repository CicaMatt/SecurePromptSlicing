import java.io.*;

class Main {
    public static void main(String[] args) throws IOException {
        File file = new File("important_config");
        if (!file.exists()) {
            file.createNewFile();
        }
        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        bw.write("important_config");
        bw.close();
    }
}