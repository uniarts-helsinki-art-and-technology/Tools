Table table;

int x = 0;
int y = 0;

void setup() {
  size(867,600);
  background(0);
  stroke(255);
  noFill();
  table = loadTable("NGC_0224 S B hbc1980.csv", "header");

  println(table.getRowCount() + " total rows in table"); 

  for (TableRow row : table.rows()) {
    
    float lambda = row.getFloat("lambda");
 //   double flux = row.getDouble("flux")*100;
    double flux = row.getDouble("flux")*1e9;
    flux*=1e7;
  //  println("Lambda: "+ lambda + ", Flux:" + flux );
    int scaled = (int) Math.floor(flux);  
    y = int(map(scaled, 0,3000,0,height));
    stroke(255);
    point(x,height-y);
    stroke(255, 10);
    ellipse(x,height-y,20,20);
    //line(x,height,x,height-y);
    x+=1;
  }
  
}