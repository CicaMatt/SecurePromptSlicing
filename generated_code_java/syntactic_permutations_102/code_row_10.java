import java.io.FileOutputStream;

class OpenFile {
    public static void main(String[] args) throws Exception{
        FileOutputStream file = new FileOutputStream("important_config", true);
        String str = "important_config";
        byte[] bytes = str.getBytes();
        file.write(bytes);

        file.close();
    }
}