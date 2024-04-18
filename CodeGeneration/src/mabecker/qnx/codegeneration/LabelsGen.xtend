package mabecker.qnx.codegeneration

import java.util.ArrayList
import mabecker.qnx.codegeneration.model.QnxLabel

class LabelsGen {
	/**
	 * Method generates the header file
	 */
	static def generateHeader(ArrayList<QnxLabel> labels) {
		'''
			#ifndef LABELS_CONF_H_
			#define LABELS_CONF_H_
			
			#include "labels.h"
			
			#define LABELS_COUNT	«labels.size»
			
			«FOR l : labels»
				#define L_«toUpper(l.name)» «labels.indexOf(l)»
			«ENDFOR»
			
			«FOR l : labels»
				/**
				 * Label «toUpper(l.name)»
				 */
				#define L_«toUpper(l.name)»_SIZE «l.size_byte»
				
				extern uint8_t l_«l.name»_dataA[L_«toUpper(l.name)»_SIZE];
				extern uint8_t l_«l.name»_dataB[L_«toUpper(l.name)»_SIZE];
				
				extern globalLabel_t l_«l.name»;
				
			«ENDFOR»
			
			
			extern globalLabel_t* labels[LABELS_COUNT];
			
			#endif //LABELS_CONF_H_
		'''
	}
	
	/**
	 * Method generates the header file
	 */
	static def generateSource(ArrayList<QnxLabel> labels) {
		'''
			#include "labels_conf.h"
			
			«FOR l : labels»
				/**
				 * Label «toUpper(l.name)»
				 */
				
				uint8_t l_«l.name»_dataA[L_«toUpper(l.name)»_SIZE];
				uint8_t l_«l.name»_dataB[L_«toUpper(l.name)»_SIZE];
				
				globalLabel_t l_«l.name» = {
					.readpos = 0,
					.dataA = l_«l.name»_dataA,
					.dataB = l_«l.name»_dataB,
					.size = L_«toUpper(l.name)»_SIZE
				};
				
			«ENDFOR»
			
			
			globalLabel_t* labels[LABELS_COUNT] = {
				«FOR l : labels»
					&l_«l.name»,
				«ENDFOR»
			};
			
		'''
	}
	
	static def toUpper(String s) {
		return s.toUpperCase;
	}
}

