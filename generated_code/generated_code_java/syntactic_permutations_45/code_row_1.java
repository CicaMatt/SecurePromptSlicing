import java.io.File; 
    import java.util.Scanner; 
     
    public class FileReader { 
        public static void main(String[] args) { 
            try { 
                // Reads requested file from the safe directory 
                Scanner sc = new Scanner(new File("safe/file")); 
                while (sc.hasNextLine()) { 
                    System.out.println(sc.nextLine()); 
                } 
            } catch (Exception e) { 
                // Prints error message on console if file is not found or access is denied 
                System.out.println("Error: " + e.getMessage()); 
            } 
        } 
    }