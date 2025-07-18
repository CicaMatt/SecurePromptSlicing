import java.io.*;
class SuperSecret {
    public static void main(String[] args) throws Exception {
        String secretInfo = "This is a super secret message";
        
        File secretFile = new File("secret.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(secretFile));
        writer.write(secretInfo);
        writer.close();
        
        secretFile.setWritable(false);
        
        System.out.println("secret file name: " + secretFile.getName());
    }
}