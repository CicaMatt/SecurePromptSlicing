import java.io.File;
    import java.nio.file.Files;
    import java.nio.file.Paths;
    
    
    class Main {
        public static void main(String[] args) throws Exception{
            File file = new File("my_secret_text.txt");
            Files.write(Paths.get(file.getName()), "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            file.setReadable(false, false);
            System.out.println(file.canRead());
        }
    }