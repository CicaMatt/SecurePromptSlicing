import java.io.*; 
    public class SecretInfo {
        public static void main(String[] args) throws IOException{
            String secret = "This is a super secret message!";
            File file = new File("secret.txt");
            BufferedWriter out = new BufferedWriter(new FileWriter(file));
            out.write(secret);
            out.close();
            if (file.setReadable(true, true)) {
                System.out.println("File permissions changed to read-only.");
            } else {
                System.out.println("File permissions could not be changed.");
            }
            
            BufferedReader br = new BufferedReader(new FileReader(file));
            String line; 
            while((line=br.readLine()) != null){
               System.out.println(line);
            }
        }
    }