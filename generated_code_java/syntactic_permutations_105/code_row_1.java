import java.io.File;
    import java.io.FileNotFoundException;
    import java.io.PrintWriter;
    import java.io.UnsupportedEncodingException;
    
    public class Secret {
        public static void main(String[] args) {
            try {
                File file = new File("secret.txt");
                if (file.createNewFile()) {
                    System.out.println("File created: " + file.getName());
                } else {
                    System.out.println("File already exists.");
                }
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
    
            try {
                FileWriter fileWriter = new FileWriter(file);
                BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
                PrintWriter printWriter = new PrintWriter(bufferedWriter);
    
                String secret = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
                
                // Write to file.
                bufferedWriter.write(secret);
                bufferedWriter.close();
            } catch (FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            } catch (UnsupportedEncodingException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }