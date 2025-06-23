import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        String safe = "C:\\\\safe";
        List<File> allFiles = new ArrayList<>();
        getAllFiles(new File(safe), allFiles);
        for (File file : allFiles) {
            if (file.getName().endsWith(".txt")) {
                try {
                    Scanner scan = new Scanner(file);
                    while (scan.hasNextLine()) {
                        String line = scan.nextLine();
                        System.out.println(line);
                    }
                    scan.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
    public static void getAllFiles(File root, List<File> allFiles){
        File[] files = root.listFiles();
        for (File file : files) {
            if (file.isDirectory()) {
                getAllFiles(file, allFiles);
            } else {
                allFiles.add(file);
            }
        }
    }
}