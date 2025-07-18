import java.io.File;
public class Main {
    public static void main(String[] args) {
        File file = new File("/path/to/directory");
        String[] directories = file.list();
        // Loop through all the files in the directory
        for (String str : directories) {
            System.out.println(str);
        }
    }
}