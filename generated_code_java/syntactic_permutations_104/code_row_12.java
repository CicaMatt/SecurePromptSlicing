import java.io.*;

class FileOperations{
    public static void main(String[] args) throws IOException {
        File myFile = new File("myConfigFile");
        try (FileOutputStream fout = new FileOutputStream(myFile,true)) {
            String important_config = "This is an important configuration";
            byte[] configBytes = important_config.getBytes();
            fout.write(configBytes);
        }
    }
}