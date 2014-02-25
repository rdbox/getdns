/*
 * Copyright (c) 2013, NLNet Labs, Verisign, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of the <organization> nor the
 *   names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Verisign, Inc. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _check_getdns_list_get_bindata_h_
#define _check_getdns_list_get_bindata_h_

    /*
     **************************************************************************
     *                                                                        *
     *  T E S T S  F O R  G E T D N S _ L I S T _ G E T _ N A M E   *
     *                                                                        *
     **************************************************************************
    */

    START_TEST (getdns_list_get_bindata_1)
    {
     /*
      *  list = NULL
      *  expect: GETDNS_RETURN_INVALID_PARAMETER
      */
      struct getdns_list *list = NULL;
      size_t index = 0;
      struct getdns_bindata *answer = NULL;

      ASSERT_RC(getdns_list_get_bindata(list, index, &answer),
        GETDNS_RETURN_INVALID_PARAMETER, "Return code from getdns_list_get_names()");
      
    }
    END_TEST

    START_TEST (getdns_list_get_bindata_2)
    {
     /* index is out of range
      * create a list and and set index 0 to an int with a value of 100 
      * Call getdns_get_list() for index 1 
      * expect: GETDNS_RETURN_INVALID_PARAMETER
     */
      struct getdns_list *list = NULL;
      size_t index = 0;

      LIST_CREATE(list);
      
      ASSERT_RC(getdns_list_set_int(list, index, 1),
        GETDNS_RETURN_GOOD, "Return code from getdns_list_set_int()");

      index++;
      ASSERT_RC(getdns_list_get_bindata(list, index, NULL),
      	GETDNS_RETURN_INVALID_PARAMETER, "Return code from getdns_list_get_bindata()");

      LIST_DESTROY(list);
    }
    END_TEST

    START_TEST (getdns_list_get_bindata_3)
    {
     /* data type at index is not int
      * create a list and set index 0 to an int with a value of 100 
      * Call getdns_list_get_bindata() for index 0
      * expect: GETDNS_RETURN_WRONG_TYPE_REQUESTED
      */
      struct getdns_list *list = NULL;
      size_t index = 0;
      struct getdns_bindata *answer = NULL;

      LIST_CREATE(list);

      ASSERT_RC(getdns_list_set_int(list, index, 1),
        GETDNS_RETURN_GOOD, "Return code from getdns_list_set_int()");


      ASSERT_RC(getdns_list_get_bindata(list, index, &answer),
        GETDNS_RETURN_WRONG_TYPE_REQUESTED, "Return code from getdns_list_get_bindata()");

      LIST_DESTROY(list);
    }
    END_TEST

    START_TEST (getdns_list_get_bindata_4)
    {
     /* answer is NULL
      * expect: GETDNS_RETURN_INVALID_PARAMETER
      */	
      struct getdns_list *list = NULL;
      size_t index = 0;

      ASSERT_RC(getdns_list_get_bindata(list, index, NULL),
        GETDNS_RETURN_INVALID_PARAMETER, "Return code from getdns_list_get_bindata()");
    }
    END_TEST

    START_TEST (getdns_list_get_bindata_5)
    {
     /* 
      * create a list
      * Create some bindata containing "bindata" and add it to the list with name = "bindata"
      * Set list value at index 0 via getdns_list_set_list() to the bindata
      * Call getdns_list_get_list() for index 0
      * expect: GETDNS_RETURN_GOOD
      */
      struct getdns_list *list = NULL;
      struct getdns_bindata bindata = { 8, (void *)"bindata" };
      size_t index = 0;
      struct getdns_bindata *answer = NULL;

      LIST_CREATE(list);

      ASSERT_RC(getdns_list_set_bindata(list, index, &bindata),
        GETDNS_RETURN_GOOD, "Return code from getdns_list_set_bindata()");


      ASSERT_RC(getdns_list_get_bindata(list, index, &answer),
        GETDNS_RETURN_GOOD, "Return code from getdns_list_get_bindata()");

      ck_assert_msg(strcmp((char *)answer->data, (char *)bindata.data) == 0, 
        "Expected bindata data to be \"%s\", got: \"%s\"",
        (char *)bindata.data, (char *)answer->data);

      LIST_DESTROY(list);
    }
    END_TEST
    
    

    

    
    Suite *
    getdns_list_get_bindata_suite (void)
    {
      Suite *s = suite_create ("getdns_list_get_bindata()");

      /* Negative test caseis */
      TCase *tc_neg = tcase_create("Negative");
      tcase_add_test(tc_neg, getdns_list_get_bindata_1);
      tcase_add_test(tc_neg, getdns_list_get_bindata_2);
      tcase_add_test(tc_neg, getdns_list_get_bindata_3);
      tcase_add_test(tc_neg, getdns_list_get_bindata_4);
      suite_add_tcase(s, tc_neg);

      /* Positive test cases */
       TCase *tc_pos = tcase_create("Positive");
       tcase_add_test(tc_pos, getdns_list_get_bindata_5);
       suite_add_tcase(s, tc_pos);

      return s;
    }

#endif
