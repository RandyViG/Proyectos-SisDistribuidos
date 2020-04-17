import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;  //Para manejo de ByteBuffer
import java.nio.ByteOrder;

import java.awt.*;

public class Graficos extends javax.swing.JFrame {
    int x0,xN,y0,yN;  //posiciones a dibujar
    double xmin,xmax,ymin,ymax;  //valores limite de la onda
    int apAncho,apAlto;  //Valores para calcular la altura y ancho de la onda
  
    public Graficos() {
        initComponents(); //Interfaz;
    }

    public void paint( Graphics g ) {
        int j1;
        DatagramSocket sock = null;
        int port = 7200,id;
        boolean band=true;
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
                g.setColor(Color.WHITE);
                g.drawLine( 400 , 0 , 400 , 600 );
                g.drawLine( 0 , 300 , 800 , 300 );
                while( true ){
                    id = 0;
                    j1 = 150;
                    if ( band == true )
                        g.setColor(Color.ORANGE);
                    else
                        g.setColor(Color.BLACK);
                    
                    for( int i=0; i < apAncho; i++ ){
                        byte[] buffer = new byte[65536];
                        DatagramPacket receive = new DatagramPacket(buffer, buffer.length);
                        sock.receive(receive);
                        byte[] data = receive.getData();
                        ByteBuffer buf = ByteBuffer.wrap(data);
                        buf.order(ByteOrder.LITTLE_ENDIAN);
            			int idd = buf.getInt();
                        int x = buf.getInt();
                        int y = buf.getInt();
			            if ( idd < id )
				            i--;
			            else{
                            id++;
                            System.out.println("id: "+ idd+ " int MIN = " + x + " int MAX = " + y);
                            g.drawLine( i,j1,x,y );
                            j1 = y;
                        }
                        ByteBuffer res =  ByteBuffer.allocate(20);
			            res.order(ByteOrder.LITTLE_ENDIAN);
			            res.putInt(id);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
                        System.out.println("Enviando ID: " + id);
			            DatagramPacket response = new DatagramPacket(res.array(),res.limit(),receive.getAddress(),receive.getPort() );
			            sock.send(response);		
                    }
                    band=!band;
                }
            }
            catch(IOException e){
                System.err.println("IOException " + e);
            }
    }
  
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 800, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 600, Short.MAX_VALUE)
        );
        super.setBackground(Color.BLACK);
        pack();
    }// </editor-fold>                        

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Graficos().setVisible(true);
            }
        });
    }
}
