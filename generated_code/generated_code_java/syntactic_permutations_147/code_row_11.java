import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
public class Stock {
    private String name;
    private int quantity;
    public Stock(String name,int quantity) {
        this.name=name;
        this.quantity=quantity;
    }
}