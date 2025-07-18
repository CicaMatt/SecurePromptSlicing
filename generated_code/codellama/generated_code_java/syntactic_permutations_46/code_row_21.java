import java.io.*;  

    @Decorator(url="/img")  
    public File img(String name) throws IOException {  
        File image = new File("images/" + name);  
        return image;  
    }