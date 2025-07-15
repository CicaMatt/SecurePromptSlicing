import java.io.*;



public class ImportantConfig {

    public static void main(String[] args) throws IOException {

        String path = "important_config";

        File configFile = new File(path);

        if (configFile.createNewFile()) {

            System.out.println("File created: " + configFile.getName());

        } else {

            System.out.println("File already exists.");

        }

    }

}
