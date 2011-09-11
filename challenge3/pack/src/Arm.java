/*
 * CuboRobot.java
 * Este programa demuestra el concepto de "Scenegraph".
 * Se arma un "dedo" articulado y el ángulo de rotación se cambia con las
 * flechas.
 */

import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.event.*;
import java.awt.GraphicsConfiguration;

import articulations.*;

import com.sun.j3d.utils.applet.MainFrame; 
import com.sun.j3d.utils.universe.*; 
import com.sun.j3d.utils.geometry.ColorCube;
import javax.media.j3d.*;
import javax.vecmath.*;
import java.awt.event.KeyEvent;


//   Este programa demuestra como usar el "scenegraph" de Java3D
//   para crear un "brazo" articulado de un robot.  

public class Arm extends Applet
	implements KeyListener  {

	double increment = 4.5d*Math.PI/180d;
	double angulo = 0d;
		
	// Articulation 1	
	Shoulder a1 = new Shoulder();	
	
	// Bone 1
	Bone s1 = new Bone(0.3d);
	
	// Articulation 2
	Elbow a2 = new Elbow();
	
	// Bone 2
	Bone s2 = new Bone(0.3d);
	
 	// Articulation 3
	Wrist a3 = new Wrist();
	
	// Bone 3
	Bone s3 = new Hand(0.3d);
	
    public Arm() {
        setLayout(new BorderLayout());
        GraphicsConfiguration config =
           SimpleUniverse.getPreferredConfiguration();

        Canvas3D canvas3D = new Canvas3D(config);
        add("Center", canvas3D);
        canvas3D.addKeyListener(this);

        BranchGroup scene = createSceneGraph();

        // SimpleUniverse is a Convenience Utility class
        SimpleUniverse simpleU = new SimpleUniverse(canvas3D);

		// This will move the ViewPlatform back a bit so the
		// objects in the scene can be viewed.
        simpleU.getViewingPlatform().setNominalViewingTransform();

        simpleU.addBranchGraph(scene);
    } // end of HelloJava3Da (constructor)

     public BranchGroup createSceneGraph() {
		// Raiz de la escena
		BranchGroup objRoot = new BranchGroup();
	
		// Subir la mitad de la longitud del primer segmento
		Transform3D t3d = new Transform3D();
		t3d.set(new Vector3d());
		TransformGroup tg0 = new TransformGroup(t3d);
		
		
		// Agregar la primera articulacion
		tg0.addChild(a1.getTransformGroup());
		// Agregar el primer segmento
		a1.getTransformGroup().addChild(s1.getTransformGroup0());
		// Agregar la segunda articulacion
		s1.getTransformGroup2().addChild(a2.getTransformGroup());
		// Agregar el segundo segmento
		a2.getTransformGroup().addChild(s2.getTransformGroup0());
		// Agregar la segunda articulacion
		s2.getTransformGroup2().addChild(a3.getTransformGroup());
		// Agregar el segundo segmento
		a3.getTransformGroup().addChild(s3.getTransformGroup0());
		// Agregar la raiz del arbol a la escena
		objRoot.addChild(tg0);
		
	
		return objRoot;
    } // end of CreateSceneGraph method of HelloJava3Da


	
	public void keyPressed(KeyEvent e) {
		
		if (e.getKeyCode() == KeyEvent.VK_Q) {
			System.out.println("Increase Y rotation at shoulder");
			a1.increaseAngleY(increment);
		}
		if (e.getKeyCode() == KeyEvent.VK_A) {
			System.out.println("Decrease Y rotation at shoulder");
			a1.increaseAngleY(-increment);			
		}
		if (e.getKeyCode() == KeyEvent.VK_W) {
			System.out.println("Increase Z rotation at shoulder");
			a1.increaseAngleZ(increment);
		}
		if (e.getKeyCode() == KeyEvent.VK_S) {
			System.out.println("Decrease Z rotation at shoulder");
			a1.increaseAngleZ(-increment);			
		}
		if (e.getKeyCode() == KeyEvent.VK_E) {
			System.out.println("Increase Z rotation at elbow");
			a2.increaseAngleZ(increment);
		}
		if (e.getKeyCode() == KeyEvent.VK_D) {
			System.out.println("Decrease Z rotation at elbow");
			a2.increaseAngleZ(-increment);			
		}
		if (e.getKeyCode() == KeyEvent.VK_R) {
			System.out.println("Increase X rotation at wrist");
			a3.increaseAngleX(increment);
		}
		if (e.getKeyCode() == KeyEvent.VK_F) {
			System.out.println("Decrease X rotation at wrist");
			a3.increaseAngleX(-increment);			
		}		
		
	}

	public void keyReleased(KeyEvent e) {
		//System.out.println(e);
	}

	public void keyTyped(KeyEvent e) {
		//System.out.println(e);
	}

    public static void main(String[] args) {
		Frame frame = new MainFrame(new Arm(), 512, 512);
    } // end of main (method of HelloJava3Da)
}
