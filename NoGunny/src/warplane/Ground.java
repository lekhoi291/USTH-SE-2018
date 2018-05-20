/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package warplane;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

/**
 *
 * @author duanp
 */
public class Ground {

    private BufferedImage groundImage;
    private int x1, x2;
    private final int y1, y2;

    /**
     * Constructor
     */
    public Ground() {
        try {
            groundImage = ImageIO.read(new File("Assets/ground5.png"));
        } catch (IOException ex) {
        }
        x1 = 0;
        y1 = 470;
        x2 = x1 + 824;
        y2 = 470;
    }

    public void update() {
        x1 -= 10;
        x2 -= 10;
        if (x1 < 0) {
            x2 = x1 + 824;
        }
        if (x2 < -0) {
            x1 = x2 + 824;
        }
    }

    public void Paint(Graphics2D g2) {
        g2.drawImage(groundImage, x1, y1, null);
        g2.drawImage(groundImage, x2, y2, null);
    }

    public int getYGround() {// return the value y of ground
        return y1;
    }
}
