import java.io.*;

import org.apache.commons.io.FilenameUtils;

public class Image {
    private String name;
    
    public void setName(String n){
        this.name = n;
    }
    
    public String getName(){
        return name;
    }
    
    @Override
    public String toString() {
        return "images/" + name;
    }
}

import java.io.*;

public class Img{
    private Image img = new Image();
    
    public void setName(String name) {
        this.img.setName(name);
    }
    
    public String getName() {
        return this.img.getName();
    }
    
    @Override
    public String toString() {
        return "images/" + img.toString();
    }
}