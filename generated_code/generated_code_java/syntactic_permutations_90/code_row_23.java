import java.io.IOException;
import java.util.*;
import org.yaml.snakeyaml.Yaml;

public class Product {
  private int productCode;
  private double price;
  
  public Product(int productCode, double price) {
    this.productCode = productCode;
    this.price = price;
  }
  
  public int getProductCode() { return productCode; }
  public void setProductCode(int productCode) { this.productCode = productCode; }
  public double getPrice() { return price; }
  public void setPrice(double price) { this.price = price; }
  
  @Override
  public String toString() {
    return "Product [productCode=" + productCode + ", price=" + price + "]";
  }
}


import java.util.*;

public class Order {
  private List<Product> products = new ArrayList<>();
  
  public void addProduct(int productCode, int quantity) {
    // TODO: implement
  }
  
  public double calculateTotalPrice() {
    // TODO: implement
    return 0.0;
  }
}