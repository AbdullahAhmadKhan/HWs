/******************************************************************************/
/*                               WALL EXPERIMENTS                             */
/******************************************************************************/

#include "Particle.h"
#include "Wall.h"
#include "CurvyWall.h"

int main(int argc, char* argv[]) {

	// Particle Experiments
	Particle* p0 = new Particle(0,0);
	Particle* p1 = new Particle(0,3);
	Particle* q0 = new Particle(0,3);
	Particle* q1 = new Particle(0,5);

	cout <<	"TEST NO 1 - Particle:: FindDistance()" << endl;
	cout << p0->FindDistance(*p1) << endl;
	cout << q1->FindDistance(*q0) << endl;
	cout << "The answer key: " << 3 << " | " << 2 << endl << endl;

	cout << "TEST NO 2 - Particle:: operator==" << endl;
	cout << (*p1 == *q0) << endl;
	Particle* px = new Particle(2,0);
	cout << (*px == *q0) << endl;
	cout << (*q0 == *px) << endl;
	cout << "The answer key: " << "1| 0 | 0"<< endl << endl;

	// Wall Experiments
	Wall* wallp = new Wall(*p0, *p1);
	Wall* wallq = new Wall(*q0, *q1);
	cout << "TEST NO 3 - Wall:: IsContinuousLinear & operator+" << endl;
	cout << (wallp->GetFinalParticle() == wallq->GetInitialParticle()) << endl;
	cout << wallp->IsContinuousLinear(*wallq) << endl;
	const Wall* wall = &(*wallp + *wallq);
	cout << wall->GetLength() << endl;
	cout << "The answer key: " << "1 | 1 | 5"<< endl << endl;

	cout << "TEST NO 4 - Wall:: ApplePearException" << endl;
	Particle* qx = new Particle(1,4);
	Wall* curvyWall = new CurvyWall(*q0, *q1, *qx);
	try {
		const Wall* apple_pear = &(*wallp + *curvyWall);
		delete apple_pear;
	} catch (ApplePearException e) {
		cout << e.what() << endl << endl;
	}
	cout << "The answer key: Should print ApplePearException message." << endl << endl;


	Particle* c1 = new Particle(2, 5);
	Particle* c2 = new Particle(-1, 4);
	Wall* wallc = new Wall(*p1, *c1);
	Wall* wallc1 = new Wall(*c1, *q1);
	Wall* ccurvyWall = new CurvyWall(*q1, *c1, *qx);
	cout << "CUSTOM TEST NO 1 - Wall:: IsContinuousLinear for Wall and Wall" << endl;
	cout << wallp->IsContinuousLinear(*wallc) << endl;
	cout << wallp->IsContinuousLinear(*wallc1) << endl;
	cout << "The answer key: Should print 0 | 0." << endl << endl;

	cout << "CUSTOM TEST NO 2 - Wall:: IsContinuousLinear for Wall and CurvyWall" << endl;
	cout << wallp->IsContinuousLinear(*curvyWall) << endl;
	cout << "The answer key: Should print 0." << endl << endl;

	cout << "CUSTOM TEST NO 3 - Wall:: IsContinuousLinear for CurvyWall and Wall" << endl;
	cout << curvyWall->IsContinuousLinear(*wallp) << endl;
	cout << "The answer key: Should print 0." << endl << endl;

	cout << "CUSTOM TEST NO 4 - Wall:: IsContinuousLinear for CurvyWall and CurvyWall" << endl;
	cout << curvyWall->IsContinuousLinear(*ccurvyWall) << endl;
	cout << "The answer key: Should print 0." << endl << endl;


	delete p0;
	delete p1;
	delete q0;
	delete q1;
	delete px;
	delete qx;
	delete c1;
	delete c2;

	delete wallp;
	delete wallq;
	delete wallc;
	delete wallc1;
	delete wall;
	delete curvyWall;
	delete ccurvyWall;

	return 0;

}
