import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Vector3d;

import com.sun.j3d.utils.geometry.ColorCube;

/*
 * Bone
 * Esta clase constituye una "falange" del dedo.
 * tg0 es el comienzo de la falange
 * tg1 es el medio de la falange
 * tg2 es el fin de la falange
 */
public class Bone {
	double length;
	// tg0 es el grupo del cual se pega este segmento a la articulaci�n pap�
	// tg1 es el grupo al cual se pega el cubo de esta articulaci�n
	// tg2 es el grupo del cual se pega la articulaci�n hija
	TransformGroup tg0, tg1, tg2;
	Transform3D t3D;
	
	public Bone(double longitud) {
		this.length = longitud;
		t3D = new Transform3D();
		t3D.set(new Vector3d(longitud/2d, 0d, 0d));
		tg0 = new TransformGroup();
		tg1 = new TransformGroup(t3D);
                Transform3D t3d11 = new Transform3D();
                t3d11.setScale(new Vector3d(1d, .5d, .5d));
                TransformGroup tg11 = new TransformGroup(t3d11);
                tg1.addChild(tg11);
		tg11.addChild(new ColorCube(longitud/2d));
		tg0.addChild(tg1);
		tg2 = new TransformGroup(t3D);
		tg1.addChild(tg2);
        }
	
	public void setLongitud(double longitud) {
		this.length = longitud;
	}
	
	public double getLongitud() {
		return length;
	}
	
	public TransformGroup getTransformGroup0() {
		return tg0;
	}
	
	public TransformGroup getTransformGroup2() {
		return tg2;
	}
}
