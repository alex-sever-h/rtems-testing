/*
 *   $Id$
 */

/*! @file Reports.h
 *  @brief Reports Specification
 *
 *  This file contains the specification of the Reports methods.  This
 *  collection of methods is used to generate the various reports of
 *  the analysis results.
 */

#ifndef __REPORTSBASE_H__
#define __REPORTSBASE_H__

#include <stdint.h>
#include <string>
#include "DesiredSymbols.h"

namespace Coverage {


class ReportsBase {

  public:
    ReportsBase();
    ~ReportsBase();

    /*!
     *  This method produces an annotated assembly listing report containing
     *  the disassembly of each symbol that was not completely covered.
     *
     *  @param[in] fileName identifies the annotated report file name
     */
    void WriteAnnotatedReport(
      const char* const fileName
    );

    /*!
     *  This method produces a report that contains information about each
     *  uncovered branch statement.
     *
     *  @param[in] fileName identifies the branch report file name
     */
    void WriteBranchReport(
      const char* const fileName
    );

    /*!
     *  This method produces a report that contains information about each
     *  uncovered range of bytes.
     *
     *  @param[in] fileName identifies the coverage report file name
     */
    void WriteCoverageReport(
      const char* const fileName
    );

    /*!
     *  This method produces a summary report that lists each uncovered
     *  range of bytes.
     *
     *  @param[in] fileName identifies the size report file name
     */
    void WriteSizeReport(
      const char* const fileName
    );

    /*!
     *  This method returns the unique extension for the Report
     *  type.  If the extension is ".txt" files will be 
     *  named "annotated.txt", "branch.txt" ......
     *
     *  @param[in] fileName identifies the size report file name
     */
    std::string ReportExtension() { return reportExtension_m; }

  protected:

    /*!
     * This type is used to track a state during the annotated output.
     */
    typedef enum {
      A_SOURCE,
      A_EXECUTED,
      A_NEVER_EXECUTED,
      A_BRANCH_TAKEN,
      A_BRANCH_NOT_TAKEN
    }AnnotatedLineState_t;

    /*!
     *  This member variable contains the extension used for all reports.
     */
    std::string reportExtension_m;


  /*!
   *  This method Opens a report file and verifies that it opended
   *  correctly.  Upon failure NULL is returned.
   *
   *  @param[in] fileName identifies the size report file name
   */
     virtual FILE* OpenFile(
      const char* const fileName
    );

  /*!
   *  This method d Opens a report file and verifies that it opended.
   *  Then appedns any necessary header information onto the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual FILE* OpenAnnotatedFile(
      const char* const fileName
    );

  /*!
   *  This method d Opens a report file and verifies that it opended.
   *  Then appedns any necessary header information onto the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual FILE* OpenBranchFile(
      const char* const fileName
    );

  /*!
   *  This method d Opens a report file and verifies that it opended.
   *  Then appedns any necessary header information onto the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual FILE* OpenCoverageFile(
      const char* const fileName
    );

  /*!
   *  This method d Opens a report file and verifies that it opended.
   *  Then appedns any necessary header information onto the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual FILE* OpenSizeFile(
      const char* const fileName
    );

  /*!
   *  This method Closes a report file. 
   *
   *  @param[in] fileName identifies the size report file name
   */
    void CloseFile(
      FILE*  aFile
    );

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void CloseAnnotatedFile(
      FILE*  aFile
    );

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void CloseBranchFile(
      FILE*  aFile
    );

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void CloseCoverageFile(
      FILE*  aFile
    );

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void CloseSizeFile(
      FILE*  aFile
    );

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void PutAnnotatedLine( 
      FILE*                aFile, 
      AnnotatedLineState_t state, 
      std::string          line,
      uint32_t             id 
    )=0;

  /*!
   *  This method puts any necessary footer information into
   *  the report then closes the file.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual bool PutNoBranchInfo(
      FILE* report
    ) = 0;

  /*!
   *  This method puts a branch entry into the branch report. 
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual bool PutBranchEntry(
      FILE*                                            report,
      unsigned int                                     number,
      Coverage::DesiredSymbols::symbolSet_t::iterator  symbolPtr,
      Coverage::CoverageRanges::ranges_t::iterator     rangePtr
    )=0;

  /*!
   *  This method reports when no range is available for 
   *  a symbol in the coverage report.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual void putCoverageNoRange(
      FILE*        report,
      unsigned int number,
      std::string  symbol
    )=0;

  /*!
   *  This method puts a line in the coverage report.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual bool PutCoverageLine(
      FILE*                                           report,
      unsigned int                                    number,
      Coverage::DesiredSymbols::symbolSet_t::iterator ditr,
      Coverage::CoverageRanges::ranges_t::iterator    ritr
    )=0;

  /*!
   *  This method method puts a line into the size report.
   *
   *  @param[in] fileName identifies the size report file name
   */
    virtual bool PutSizeLine(
      FILE*                                           report,
      unsigned int                                    number,
      Coverage::DesiredSymbols::symbolSet_t::iterator symbol,
      Coverage::CoverageRanges::ranges_t::iterator    range
    )=0;
};

void GenerateReports();

}

#endif