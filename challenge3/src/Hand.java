import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Vector3d;

import com.sun.j3d.utils.geometry.ColorCube;


public class Hand extends Bone {
	public Hand(double length) {
		super(length);
		this.length = length;
		t3D = new Transform3D();
		t3D.set(new Vector3d(length/2d, 0d, 0d));
		
		tg0 = new TransformGroup();
		tg1 = new TransformGroup(t3D);
                Transform3D t3d11 = new Transform3D();
                t3d11.setScale(new Vector3d(1d, .7d, .1d));
                TransformGroup tg11 = new TransformGroup(t3d11);
                tg1.addChild(tg11);
		tg11.addChild(new ColorCube(length/2d));
		tg0.addChild(tg1);
		tg2 = new TransformGroup(t3D);
		tg1.addChild(tg2);
    }
}	

