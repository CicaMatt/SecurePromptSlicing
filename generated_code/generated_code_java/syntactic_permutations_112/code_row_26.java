import java.io.*;
    import java.net.*;
    
    public class PingDecorator implements Decorator{
        private String url;
    
        public void setUrl(String url){
            this.url = url;
        }
        public String ping(){
            return "Pong";
        }
    }