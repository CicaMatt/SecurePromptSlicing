import java.io.*;
public class Ping {
    private String url;
    public void setUrl(String url) {
        this.url = url;
    }
    public void getUrl(){
        return url;
    }
}

### Explanation:
The decorator tells the web application what URL should trigger our function, which is ping(). The function takes the URL from the URL and stores it in a variable called url. Then, the function runs the ping command using the system command ping. The output of the ping command is stored in a variable called output. Finally, the function returns the output of the ping command.