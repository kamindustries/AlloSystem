#ifndef AL_CONVOLVER_H
#define AL_CONVOLVER_H

#include <vector>

#include "allocore/io/al_AudioIO.hpp"

class Convproc;

namespace al {

using namespace std;


// Number of IRs must always match the number of output channels
// Use cases:
// - Decorrelation: many to many each with a different IR
// - Auralization: one to many each with a different IR
//               : many to many each with a different IR
// - DRC : many to many each with different IR
// - Synthesized source:


class Convolver
{

public:
    Convolver();

	/**
	 * @brief configure
	 *
	 * Output from disabled channels is set to 0.
	 *
	 * @param io
	 * @param IRs
	 * @param inputs
	 * @param inputsAreBuses
	 * @param disabledChannels
	 * @param maxsize
	 * @param minpartition
	 * @param maxpartition
	 * @return
	 */
	int configure(al::AudioIO &io,
				  vector<float *> IRs,
				  vector<int> inputs = vector<int>(),
				  bool inputsAreBuses = false,
				  vector<int> disabledChannels = vector<int>(),
				  unsigned int maxsize = 0,
				  unsigned int minpartition = 0,
				  unsigned int maxpartition = 0);
	/**
	 * @brief processBlock
	 * @param io
	 * @return
	 */
	int processBlock(al::AudioIO io);

private:
	vector<int> m_activeChannels;
	vector<int> m_disabledChannels;
	vector<int> m_inputs;
	bool m_inputsAreBuses;
	Convproc *m_Convproc;
};

}

#endif // AL_CONVOLVER_H