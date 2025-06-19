import java.io.*;

class ImportantConfig {
    public static void main(String[] args) throws Exception {
        FileOutputStream fout = new FileOutputStream("config.txt", true);
        DataOutputStream out = new DataOutputStream(fout);
        out.writeBytes("important_config");
        out.close();
    }
}