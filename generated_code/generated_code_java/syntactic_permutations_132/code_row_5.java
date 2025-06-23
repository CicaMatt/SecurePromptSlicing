package main;
import java.io.*;
import java.util.*;

public class Hello extends Application {
    public void init() {
        // Configure Spark
        port(8080);
        get("/hello/:name", (req, res) -> "Hello " + req.params(":name"));
    }
}