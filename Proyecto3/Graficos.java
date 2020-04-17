import java.io.*;
import java.net.*;
import java.awt.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Graficos extends javax.swing.JFrame {
  
    public Graficos() {
        initComponents();
    }

    public void paint( Graphics g ) {
        int j1;
        DatagramSocket sock = null;
        int port = 7200, id = 0, idd, x,y;
        ByteBuffer res =  ByteBuffer.allocate(20);
        DatagramPacket receive,response;
        boolean band=true;
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
                g.setColor(Color.WHITE);
                g.drawLine( 400,0,400,600 );
                g.drawLine( 0,300,600,300 );
                while( true ){
                    j1 = 150;
                    if (band==true)
                        g.setColor(Color.ORANGE);
                    else
                        g.setColor(Color.BLACK);
                    for( int i=0 ; i < 800 ; i++ ){
                        byte[] buffer = new byte[65536];
                        receive = new DatagramPacket(buffer, buffer.length);
                        sock.receive(reply);
                        byte[] data = reply.getData();
                        ByteBuffer buf = ByteBuffer.wrap(data);
                        buf.order( ByteOrder.LITTLE_ENDIAN );
            			idd = buf.getInt();
                        x = buf.getInt();
                        y = buf.getInt();
			            if ( idd < id )
				            i--;
			            else{
                            id++;
                            g.drawLine( i,j1,x,y );
                            j1 = y;
                        }
			            res.order( ByteOrder.LITTLE_ENDIAN );
			            res.putInt(id);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
			            response = new DatagramPacket(res.array(),res.limit(),receive.getAddress(),receive.getPort() );
			            sock.send( response );		
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
