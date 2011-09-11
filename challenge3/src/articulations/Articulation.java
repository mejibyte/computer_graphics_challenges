package articulations;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;

/*
 * Articulation
 * Esta clase maneja las "articulaciones" que unen las falanges
 * La articulaci—n tiene solamente un TransformGroup que se llama tg.
 */
public abstract class Articulation {
	TransformGroup tg;
	Transform3D t3D;
	
	public Articulation() {
		t3D = new Transform3D();
		// No transformation
		tg = new TransformGroup(t3D);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	}

	public TransformGroup getTransformGroup() {
		return tg;
	}
}